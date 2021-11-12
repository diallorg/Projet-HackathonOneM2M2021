const mongoose = require('mongoose');

const applicationEntitySchema = new mongoose.Schema({
  name: String,
  pos: Array,
  mn: String,
  ri: String,
  lastFlame: String,
  lastHumidity: Number,
  lastTemperature: Number,
  lastWindSpeed:Number
});
const ApplicationEntity = mongoose.model('applicationentity', applicationEntitySchema);

module.exports = ApplicationEntity;