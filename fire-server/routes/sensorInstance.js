const express = require('express');
const router = express.Router();
const SensorInstance = require('../model/SensorInstance');

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
  newSensorInstance.save((err, insertedSensorInstance) => {
    if(err) res.statusCode(300);
    res.send(insertedSensorInstance);
  })
}

module.exports = router;