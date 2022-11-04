const typeAndData = require("./variables.json");
const fs = require("fs");
const pathH = "app/static/";
const dotH = "types.h";
const pathC = "app/static/";
const dotC = "types.c";
const types = typeAndData.types;
const structs = typeAndData.structs;

function buildCustomType(element) {
  let myTypeToWrite;
  if (element.type != "enum") {
    myTypeToWrite = `
/**
* \\typedef ${element.name}
* \\brief ${element.comments}
*/
typedef ${element.declaration} ${element.name};
`;
  } else {
    myTypeToWrite = `
/**
* \\enum ${element.name}
* \\brief ${element.comments}
*/
typedef enum ${element.name} {
    ${element.declaration.toString()}
}${element.name};
`;
  }
  return myTypeToWrite;
}

function buildGetterAndSetter(element, structName) {
  let getter = `
${element.type} get${element.name}() {
    return (${structName}.${element.name});
}`;

  let setter = `
void set${element.name}(${element.type} val) {
    if(${types.filter((x) => x.name == element.type)[0].domain}) {
    ${structName}.${element.name} = val;
    } else {
        printf("Error, value not in domain");
    }
}`;
  return `
    ${getter}

    ${setter}
    `;
}

function buildGetterAndSetterHeader(element) {
  let getter = `
/*!
*  \\fn ${element.type} get${element.name}()
*  \\brief get param ${element.name}
*  \\return ${element.name} ${element.type}
*/
${element.type} get${element.name}();`;

  let setter = `
/*!
*  \\fn void set${element.name}(${element.type} val)
*  \\brief set param ${element.name} 
*  \\param ${element.name} val : value to be setted
*/
void set${element.name}(${element.type} val);`;
  return `
    ${getter}

    ${setter}
    `;
}

async function writeToFile(myType, path, file) {
  try {
    fs.appendFileSync(path + file, myType, (err) => {
      if (err) throw err;
    });
  } catch (error) {
    console.error(error);
  }
}

async function initFiles() {
  let headerC = `
/*! 
*  \\file ${dotC}
*  \\author LEFLOCH Thomas <leflochtho@eisti.eu>
*/
#include "${dotH}"
`;

  let headerH = `
#ifndef TYPES_H
#define TYPES_H
/*! 
*  \\file ${dotH}
*  \\author LEFLOCH Thomas <leflochtho@eisti.eu>
*/

// Inclusion des entetes de librairies
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
    
    `;

  try {
    fs.unlinkSync(pathH + dotH);
    fs.unlinkSync(pathC + dotC);
  } catch (error) {
    console.error("Can't delete files, error. " + error);
  }

  await writeToFile(headerC, pathC, dotC);
  await writeToFile(headerH, pathH, dotH);
}

function endFiles() {
  let enderH = `
#endif
    `;

  writeToFile(enderH, pathH, dotH);
}

function buildStructInit(data) {
  let defaultVal = "";
  data.content.forEach((element) => {
    defaultVal += `${element.initVal},`;
  });
  defaultVal = defaultVal.substring(0, defaultVal.length - 1);
  return `static ${data.typedef} ${data.name} = {${defaultVal}};`;
}

function buildStruct(data) {
  let contentIn = "";
  data.content.forEach((element) => {
    contentIn += `${element.type} ${element.name};
    `;
  });

  let struct = `
    /*!
 *  \\struct ${data.name}
 *  \\brief ${data.desc}
 */
typedef struct ${data.name} {
     ${contentIn}
}${data.typedef};
`;
  return struct;
}

function entryPoint() {
  types.forEach((element) => {
    writeToFile(buildCustomType(element), pathH, dotH);
  });

  structs.forEach((struct) => {
    writeToFile(buildStructInit(struct), pathC, dotC);
    struct.content.forEach((element) => {
      writeToFile(
        buildGetterAndSetter(element, struct.name, struct.typedef),
        pathC,
        dotC
      );
      writeToFile(
        buildGetterAndSetterHeader(element, struct.name),
        pathH,
        dotH
      );
    });
    writeToFile(buildStruct(struct), pathH, dotH);
  });
}

initFiles()
  .then(() => entryPoint())
  .then(() => endFiles());
