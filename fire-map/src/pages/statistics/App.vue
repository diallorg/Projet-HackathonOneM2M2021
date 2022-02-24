<template>
  <div>
    <chart  :data="sensorInstances" />
  </div>
</template>

<script>

import axios from 'axios';
import chart from './components/chart.vue'

export default {
  components: {
    chart
  },
  data () {
    return {
      // fire-map server ip
      ip: "http://localhost:4000",
      sensorInstances: [],
      test: {
        labels: ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'],
        datasets: [
          {
            label: 'Humidity',
            borderColor: '#4FAFFF',
            fill: false,
            data: [60, 20, 12, 39, 10, 40, 39, 30, 40, 20, 12, 11]
          },
          {
            label: 'Wind speed',
            borderColor: '#00FF7F',
            fill: false,
            data: [12, 18, 25, 35, 48, 40, 39, 2, 40, 20, 12, 11]
          },
          {
            label: 'Temperature',
            borderColor: '#FFB03A',
            fill: false,
            data: [2, 4, 8, 12, 10, 17, 20, 15, 52, 12, 12, 11]
          }
        ]
    }
    };
  },
  mounted(){
    this.getServerSensorInstanceValues();
  },
  methods:{
    getServerSensorInstanceValues(){
      axios.get(this.ip + "/sensor-instances/1")
      .then(response => {
        this.sensorInstances = [];
        let labels = [];
        let datasets = [];
        let dataHumidity = [];
        let dataWind = [];
        let dataTemp = [];
        response.data.forEach(data => {
          if(data.date){
            labels.push(data.date);
            dataHumidity.push(data.humidity);
            dataWind.push(data.windSpeed);
            dataTemp.push(data.temperature);
          }
        });
        datasets = [
            {
            label: 'Humidity',
            borderColor: '#4FAFFF',
            fill: false,
            data: dataHumidity
          },
          {
            label: 'Wind speed',
            borderColor: '#00FF7F',
            fill: false,
            data: dataWind
          },
          {
            label: 'Temperature',
            borderColor: '#FFB03A',
            fill: false,
            data: dataTemp
          }
        ]
        this.sensorInstances.labels = labels;
        this.sensorInstances.datasets = datasets;
      });
      setTimeout(this.getServerSensorInstanceValues, 10000);
    }
  }
}
</script>
