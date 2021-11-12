const mongoose = require('mongoose');

const containerSchema = new mongoose.Schema({
  id: String,
  ri: String,
  pi: String,
  type: String,
  pos: Array,
  aEId: String,
  path: String
});
const Container = mongoose.model('container', containerSchema);

module.exports = Container;