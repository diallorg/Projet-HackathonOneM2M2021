const mongoose = require('mongoose');

const SensorInstanceSchema = new mongoose.Schema({
  sensorId: Number,
  humidity: Number,
  windSpeed: Number,
  temperature: Number,
  date: Date
});
const SensorInstance = mongoose.model('sensorInstance', SensorInstanceSchema);

module.exports = SensorInstance;