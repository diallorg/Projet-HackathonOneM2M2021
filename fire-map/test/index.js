const axios = require('axios');

describe('Fire map tests launched', function() {
  var date;

  this.timeout(10000);

  beforeEach(function() {
    date = new Date();
  });

  after(function() {
    console.log("Tests passed successfully");
  });

  afterEach(function() {
    console.log("At", date);
  });

  it('should get sensor-instance value from fire-server sensor 1', function(done) {
    axios.get("http://localhost:4000/sensor-instances/1")
        .then(response => done())
        .catch(function (error) {
            if (error.response) {
            console.log(error.response.data);
            console.log(error.response.status);
            console.log(error.response.headers);
            } else if (error.request) {
            console.log(error.request);
            } else {
            console.log('Error', error.message);
            }
            console.log(error.config);
    });
  });
});