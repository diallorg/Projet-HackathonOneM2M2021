const express = require('express');
const router = express.Router();
const uuid = require('uuid');
const Hydrant = require('../model/HydrantModel');

// Get all hydrants
router.post('/', function(req, res) {
  console.log(">>>>>>>>>> Receiving sensor instance.");
  
});

module.exports = router;