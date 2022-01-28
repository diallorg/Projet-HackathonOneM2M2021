const express = require('express');
const router = express.Router();
const Container = require('../../model/ContainerModel');
const ApplicationEntity = require('../../model/ApplicationEntityModel');

router.post('/', function(req, res){
  res.send();
  if(req.body['m2m:sgn']["m2m:vrq"] == true){
    console.log("Successfully subscribed to windSpeed.");
    return;
  }
  console.log(">>>>>>>>>> Receiving wind speed.");
  const con = req.body['m2m:sgn']["m2m:nev"]["m2m:rep"]["m2m:cin"].con;
  const pi = req.body['m2m:sgn']["m2m:nev"]["m2m:rep"]["m2m:cin"].pi;
  saveToDB();
  async function saveToDB(){
    let cnt = await Container.findOne({ri: pi});
    ApplicationEntity.findOneAndUpdate({ri:cnt.pi}, {lastWindSpeed: con},(err, ae)=>{
      if(err)
        console.error(error);
      else
        console.log(`Changed wind speed of ${ae.name}, new value : ${con}.`);
    });
  }
})

module.exports = router;