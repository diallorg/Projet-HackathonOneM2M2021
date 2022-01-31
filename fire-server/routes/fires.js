const express = require('express');
const router = express.Router();
const uuid = require('uuid');
const ApplicationEntity = require('../model/ApplicationEntityModel');

router.get('/', function(req, res) {
  console.log(">>>>>>>>>> Receiving fires get request.");
  ApplicationEntity.find({lastFlame: "ON"},(err, aEs)=>{
    fires = [];
    aEs.forEach(el => {
      fires.push({id: uuid.v4(), center: el.pos})
    });
    res.send(fires);
    console.log("<<<<<<<<<< Sending fires.");
  })
});

module.exports = router;