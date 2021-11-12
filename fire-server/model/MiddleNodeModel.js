const mongoose = require('mongoose');

const MiddleNodeSchema = new mongoose.Schema({
  name: String,
  poa: String,
});
const MiddleNode = mongoose.model('middlenode', MiddleNodeSchema);

module.exports = MiddleNode;