<template>
  <div>
    
  </div>
</template>

<script>

export default {
  components: {
    
  },
  data () {
    return {
      // fire-map server ip
      ip: "http://localhost:4000",
      sensorInstances: []
    };
  },
  mounted(){
    this.getServerSensorInstanceValues();
  },
  methods:{
    getServerSensorInstanceValues(){
      axios.get(this.ip + "/sensor-instance")
      .then(response => {
        this.sensorInstances = [];
        response.data.forEach(data => {
          this.sensorInstances.push(data);
        });
      })
      .catch(e => {
        this.errors.push(e);
      });

      setTimeout(this.getServerSensorInstanceValues, 10000);
    }
  }
}
</script>
