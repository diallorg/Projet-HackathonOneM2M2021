<script>
import { Line } from 'vue-chartjs'

export default {
  extends: Line,
  props: ['data', 'options'],
  mounted () {
    // Overwriting base render method with actual data.
    this.renderChart(this.data, this.options
      /*{
      labels: ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'],
      datasets: [
        {
          label: 'Humidity',
          borderColor: '#4FAFFF',
          fill: false,
          data: [40, 20, 12, 39, 10, 40, 39, 30, 40, 20, 12, 11]
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
    }*/)
  }
}
</script>