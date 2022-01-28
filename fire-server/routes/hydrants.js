const express = require('express');
const router = express.Router();
const uuid = require('uuid');
const Hydrant = require('../model/HydrantModel');

// Get all hydrants
router.get('/', function(req, res) {
  console.log(">>>>>>>>>> Receiving hydrants get request.");
  Hydrant.find({},(err, hydrants)=>{
    res.send(hydrants);
    console.log("<<<<<<<<<< Sending hydrants.");
  })
});

module.exports = router;