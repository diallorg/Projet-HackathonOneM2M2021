const express = require('express');
const config = require('../middleware/config');
const mongoose = require('mongoose');
const SensorInstance = require('../model/SensorInstanceModel');

describe('Fire Server tests launched', function() {
  var app,
      date;

  this.timeout(10000);

  before(function(done) {
    app = express();
    app.listen(config.AEPort, function(err) {
      if (err) { return done(err); }
      done();
    });
  });

  beforeEach(function() {
    date = new Date();
  });

  after(function(done) {
    console.log("Tests passed successfully");
    done()
  });

  afterEach(function() {
    console.log("At", date);
  });

  it('should connect to mongodb database', function(done) {
    mongoose.connect(config.mongoDBLink).then(() => {
      done();
    }, err => {
      throw new Error(err.message);
    })
  });

  it('should get data from database', function(done) {
    SensorInstance.findOne({}).then(() => {
      done();
    }, err => {
      throw new Error(err.message);
    })
  });

});