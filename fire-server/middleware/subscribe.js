const MiddleNode = require("../model/MiddleNodeModel");
const config = require("./config");
const request = require('request');
const Container = require("../model/ContainerModel");
const { AEPort } = require("./config");
const ApplicationEntity = require("../model/ApplicationEntityModel");

async function subscribe(){
  console.log("-------------------- SUBSCRIBING --------------------");
  console.log("Getting all MNs from database.");
  // Getting all Middlenodes
  allMNs = await MiddleNode.find({});
  // For each middlenode
  for (let index = 0; index < allMNs.length; index++) {
    const MN = allMNs[index];
    // Getting all Containers of this middlenode
    console.log(`Getting all containers from MN : ${MN.name}.`);
    allCnts = await Container.find({});
    let MnCnts = [];
    allCnts.forEach(el => {
      if(el.path.split("/")[2] == MN.name){
        MnCnts.push(el);
      }
    });
    // for each container
    for (let i = 0; i < MnCnts.length; i++) {
      const cnt = MnCnts[i];
      const aE = await ApplicationEntity.findOne({ri: cnt.pi});
      // for each sensor set in Vue.config.keyCodes = {
      for (let j = 0; j < config.sensors.length; j++) {
        const element = config.sensors[j];
        // If the containers equals the type
        if(cnt.type == element){
          console.log(`Creating subscription in ${aE.name} to Container ${element}.`);
          // Subscribes to it
          let res = await createSubscription(MN, cnt, "POST", element);
          // If it already exist
          if(res == "Name already present in the parent collection."){
            createSubscription(MN, cnt, "PUT", element);
          }
        }
      }
    }
  }
}
// Subscribes to a container
function createSubscription(MN, Cnt, method, field){
	var method = method;
	var uri = method == "POST" ? `${MN.poa}~${Cnt.path}` : `${MN.poa}~${Cnt.path}/subFireServer`;
	var resourceType = 23;
	var representation = method == "POST" ? {
		"m2m:sub": {
			"rn": "subFireServer",
			"nu": [`http://${config.AEIp}:${AEPort}/send/${field}`],
      "nct": 2
		}
	} :
  {
		"m2m:sub": {
			"nu": [`http://${config.AEIp}:${AEPort}/send/${field}`],
      "nct": 2
		}
	} 
	var options = {
		uri: uri,
		method: method,
		headers: {
			"X-M2M-Origin": "admin:admin",
			"Content-Type": `application/json;ty=${resourceType}`
		},
		json: representation
	};
  return new Promise((resolve,reject) => {
    request(options, function (error, response, body) {
      if(error){
        console.log(error);
      }else{
        resolve(body)
      }
    });
  });
}
module.exports = subscribe;