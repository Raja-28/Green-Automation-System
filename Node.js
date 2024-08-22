const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({ extended: true }));

app.post('/update', (req, res) => {
  const { soilMoisture, temperature, humidity, lightLevel } = req.body;
  console.log(`Soil Moisture: ${soilMoisture}`);
  console.log(`Temperature: ${temperature}`);
  console.log(`Humidity: ${humidity}`);
  console.log(`Light Level: ${lightLevel}`);
  
  // You can add code here to save the data to a database
  
  res.send('Data received');
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
