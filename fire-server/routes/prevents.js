const express = require('express');
const router = express.Router();
const uuid = require('uuid');
const ApplicationEntity = require('../model/ApplicationEntityModel');

router.get('/', function(req, res) {
  console.log(">>>>>>>>>> Receiving prevents get request.");
  ApplicationEntity.find({}, (err, aEs) => {
    prevents = [];
    aEs.forEach(el => {
      if(el.lastHumidity !== undefined || el.lastTemperature !== undefined || el.lastWindSpeed !== undefined){
        const fdi = 2 * Math.pow(10, -0.45 + 0.987 * Math.log(5)-0.0345 * el.lastHumidity + 0.0338 * el.lastTemperature + 0.0234 * el.lastWindSpeed);
        const radius = (1000 * el.lastWindSpeed) / 2;
        let color = "";
        if (fdi < 25)
          return;
        else if (fdi < 75)
          color = "orange";
        else
          color = "red";
        prevents.push({id: uuid.v4(), center: el.pos, color: color, radius: radius});
      }
    });
    res.send(prevents);
    console.log("<<<<<<<<<< Sending prevents.");
  })
});

module.exports = router;