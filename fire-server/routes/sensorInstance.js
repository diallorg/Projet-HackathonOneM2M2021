const express = require('express');
const router = express.Router();
const SensorInstance = require('../model/SensorInstanceModel');

// Get all sensor-instances
router.get('/:sensorId', (req, res) => {
  SensorInstance.find({id: req.params.sensorId},(err, sensorInstancesList)=>{
    if(err) return res.statusCode(300);
    if(!sensorInstancesList) return res.statusCode(404);
    res.send(sensorInstancesList);
  })
});

router.post('/'), (req, res) => {

  let newSensorInstance = new SensorInstance(req.body.sensorInstance)
  // TODO calculate the fdi
  newSensorInstance.fdi=2 * Math.pow(10, -0.45 + 0.987 * Math.log(5)-0.0345 * newSensorInstance.humidity + 0.0338 * newSensorInstance.temperature+ 0.0234 * newSensorInstance.windSpeed);
  newSensorInstance.save((err, insertedSensorInstance) => {
    if(err) res.statusCode(300);
    res.send(insertedSensorInstance);
  })
}

module.exports = router;