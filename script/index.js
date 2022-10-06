const typeAndData = require("./variables.json");
const fs = require("fs");
const { exit } = require("process");
const pathH = "include/";
const dotH = "types.h";
const pathC = "src/";
const dotC = "types.c";
const types = typeAndData.types;
const data = typeAndData.data;

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

function buildGetterAndSetter(element) {
  let getter = `
${element.type} get${element.name}() {
    return (bcgvDATA.${element.name});
}`;

  let setter = `
void set${element.name}(${element.type} val) {
    if(${types.filter((x) => x.name == element.type)[0].domain}) {
    bcgvDATA.${element.name} = val;
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
*  \\brief 
*  \\param 
*  \\return ${element.name}
*/
${element.type} get${element.name}();`;

  let setter = `
/*!
*  \\proc void set${element.name}()
*  \\brief 
*  \\param 
*  \\return ${element.name}
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
    exit(-1);
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
  data.forEach((element) => {
    defaultVal += `${element.initVal},`;
  });
  defaultVal = defaultVal.substring(0, defaultVal.length - 1);
  return `static data_t bcgvDATA = {${defaultVal}};`;
}

function buildStruct(data) {
  let content = "";
  data.forEach((element) => {
    content += `${element.type} ${element.name};
    `;
  });

  let struct = `
    /*!
 *  \\struct data
 *  \\brief Entire data of the program
 */

typedef struct data {
     ${content}
}data_t;
`;
  return struct;
}

function entryPoint() {
  types.forEach((element) => {
    writeToFile(buildCustomType(element), pathH, dotH);
  });

  writeToFile(buildStructInit(data), pathC, dotC);

  data.forEach((element) => {
    writeToFile(buildGetterAndSetter(element), pathC, dotC);
    writeToFile(buildGetterAndSetterHeader(element), pathH, dotH);
  });

  writeToFile(buildStruct(data), pathH, dotH);
}

initFiles()
  .then(() => entryPoint())
  .then(() => endFiles());
