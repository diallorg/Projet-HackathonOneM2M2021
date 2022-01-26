const express = require('express');
const router = express.Router();
const SensorInstance = require('../model/SensorInstanceModel');

// Get all hydrants
router.post('/', (req, res) => {
  console.log(">>>>>>>>>> Receiving sensor instance.");
  const newSensorInstance = new SensorInstance(req.body.sensorInstance)
  newSensorInstance.save((err, sensorInstance) => {
    if (err) {throw new Error(err);}
    res.send(sensorInstance);
  })
});

router.get('/', (_req, res) => {
 SensorInstance.find({}, (err, sensorInstances) => {
   if (err) {throw new Error(err);}
   res.send(sensorInstances);
 })
})

module.exports = router;