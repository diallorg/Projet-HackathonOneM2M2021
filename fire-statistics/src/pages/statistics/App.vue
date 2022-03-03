<template>
  <div>
    <chart v-if="dataRetrieves" :data="sensorInstances" />
  </div>
</template>

<style>
  div{
    max-width: 70%;
    display: block;
    margin-left: auto;
    margin-right: auto;
  }
</style>

<script>

import axios from 'axios';
import moment from 'moment';
import chart from './components/chart.vue'

export default {
  components: {
    chart
  },
  data () {
    return {
      // fire-statistics server ip
      ip: "http://localhost:4000",
      sensorInstances: [],
      dataRetrieves: false,
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
            let f = moment(data.date, "YYYY-MM-DD")
                    .hour(data.date.substring(11, 13))
                    .minute(data.date.substring(14, 16))
                    .second(data.date.substring(17, 19));
            labels.push(f.format('MM/DD/YYYY, h:mm:ss'));
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
        this.sensorInstances.labels = labels.sort((a, b) => {
          return new Date(a) - new Date(b);
        });
        this.sensorInstances.datasets = datasets;
        this.dataRetrieves = true;
      });
      setTimeout(this.getServerSensorInstanceValues, 10000);
    }
  }
}
</script>
