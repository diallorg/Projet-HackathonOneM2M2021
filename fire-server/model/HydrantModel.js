const mongoose = require('mongoose');

const hydrantSchema = new mongoose.Schema({
  id: Number,
  center: Array,
  creationTime: String
});
const Hydrant = mongoose.model('hydrant', hydrantSchema);

module.exports = Hydrant;