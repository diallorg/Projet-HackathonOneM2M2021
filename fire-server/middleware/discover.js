var request = require('request');
const MiddleNode = require('../model/MiddleNodeModel');
const ApplicationEntity = require('../model/ApplicationEntityModel')
const mongoose = require('mongoose');
const Container = require('../model/ContainerModel');
const config = require("./config");
// Set the infrastructure node ip
const iNodeIp = "http://"+ config.INIp + ":" + config.INIPort + "/~";

async function discover(){
  console.log("-------------------- DISCOVERING --------------------");
  console.log("Deleting MNs, AEs and Cnts from Database.");
  // Delete all MiddleNodes, Application entities and containers from database
  await MiddleNode.deleteMany();
  await ApplicationEntity.deleteMany();
  await Container.deleteMany();
  console.log("Getting all MNs Paths.");
  let mNsPaths = JSON.parse(await getRequest(`${iNodeIp}/in-cse?fu=1&ty=16`));
  // For each MN path we found
  for (let index = 0; index < mNsPaths['m2m:uril'].length; index++) {
    let path = mNsPaths['m2m:uril'][index];
    console.log(`Getting MN from ${path}`);
    let mNData = JSON.parse(await getRequest(`${iNodeIp}${path}?rcn=1`));
    let mNPOA = mNData["m2m:csr"]["poa"][0];
    let mNName = mNData["m2m:csr"]["rn"];
    let newMN = new MiddleNode({name: mNName, poa:mNPOA});
    console.log(`Saving MN : ${newMN.name} in database.`);
    // Save the new MiddleNode in the database
    await newMN.save();
    console.log(`Getting all AEs paths ${newMN.name}.`);
    let aEsPaths = JSON.parse(await getRequest(`${newMN.poa}~/mn-cse/${newMN.name}?fu=1&ty=2`));
    // for each AE path we found
    for (let index = 0; index < aEsPaths['m2m:uril'].length; index++) {
      const aEPath = aEsPaths['m2m:uril'][index];
      console.log(`Getting AE from ${aEPath}`);
      aEData = JSON.parse(await getRequest(`${newMN.poa}~${aEPath}`));
      if(!aEData['m2m:ae'].hasOwnProperty('lbl'))
        continue
      aEName = aEData['m2m:ae'].rn;
      aERi = aEData['m2m:ae'].ri;
      aEPos = aEData['m2m:ae'].lbl;
      let newAE = new ApplicationEntity({ri:aERi, name: aEName, pos: aEPos, mn:newMN.name, lastFlame: "OFF"});
      console.log(`Saving AE : ${newAE.name} in database.`);
      // save the AE in the database
      await newAE.save();
    }
    cntsPaths = JSON.parse(await getRequest(`${newMN.poa}~/mn-cse/${newMN.name}?fu=1&ty=3`));
    // for each container we found
    for (let index = 0; index < cntsPaths["m2m:uril"].length; index++) {
      const path = cntsPaths["m2m:uril"][index];
      console.log(`Getting Cnt from ${path}.`);
      cntData = JSON.parse(await getRequest(`${newMN.poa}~${path}`));
      const aE = await ApplicationEntity.findOne({pi:cntData['m2m:cnt'].ri});
      cntType = cntData['m2m:cnt'].rn;
      cntId = cntData['m2m:cnt'].ri.split('/')[2];
      cntRi = cntData['m2m:cnt'].ri;
      cntPi = cntData['m2m:cnt'].pi;
      cntPath = cntData['m2m:cnt'].ol.replace('/ol', '');
      newCnt = new Container({id: cntId, ri:cntRi, pi:cntPi, type: cntType, pos: aE.pos, aEId: aE.id, path: cntPath});
      console.log(`Saving from ${aE.name} Cnt : ${newCnt.type}`);
      // save the Container in the database
      await newCnt.save();
    }
  }
}

function getRequest(uri){
  return new Promise((resolve, reject)=>{
    request({
      method: "GET",
      uri: uri,
      headers: {
        "X-M2M-Origin": "admin:admin",
        "Content-Type": "application/json"
      }
    }, (error, response, body) => {
      if (error) reject(error);
      resolve(body);
  });
  })
}

module.exports = discover;