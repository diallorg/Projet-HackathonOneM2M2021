const express = require('express');
const router = express.Router();
const Container = require('../../model/ContainerModel');
const ApplicationEntity = require('../../model/ApplicationEntityModel');
const spawn = require("child_process").spawn;


router.post('/', function(req, res){
  res.send();
  if(req.body['m2m:sgn']["m2m:vrq"] == true){
    console.log("Successfully subscribed to flame.");
    return;
  }
  console.log(">>>>>>>>>> Receiving flame.");
  const con = req.body['m2m:sgn']["m2m:nev"]["m2m:rep"]["m2m:cin"].con;
  const pi = req.body['m2m:sgn']["m2m:nev"]["m2m:rep"]["m2m:cin"].pi;
  saveToDB();
  async function saveToDB(){
    let cnt = await Container.findOne({ri: pi});
    let ae = await ApplicationEntity.findOne({ri:cnt.pi});
    if(ae.lastFlame == "OFF" && con == "ON"){
      console.log(`Fire detected on ${ae.name}.`);
      console.log("Sending text message.");
      spawn('python',["../sms-sending/senderSMS.py"]);
    }
    ae.lastFlame = con;
    ae.save();
  }
});



module.exports = router;