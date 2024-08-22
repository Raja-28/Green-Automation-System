import React, { useState, useEffect } from 'react';
import axios from 'axios';

const SensorData = () => {
  const [data, setData] = useState({ soilMoisture: '', temperature: '', humidity: '', lightLevel: '' });

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get('http://yourserver.com/sensorData'); // Replace with your server URL
        setData(response.data);
      } catch (error) {
        console.error('Error fetching sensor data', error);
      }
    };

    fetchData();
  }, []);

  return (
    <div>
      <h1>Sensor Data</h1>
      <p>Soil Moisture: {data.soilMoisture}</p>
      <p>Temperature: {data.temperature} °C</p>
      <p>Humidity: {data.humidity} %</p>
      <p>Light Level: {data.lightLevel}</p>
    </div>
  );
};

export default SensorData;
