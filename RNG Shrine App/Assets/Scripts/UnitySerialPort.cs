using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using System;

namespace RNG
{
    public class UnitySerialPort : MonoBehaviour
    {
        [SerializeField]
        private int readTimeout = 10;
        [SerializeField]
        private int writeTimeout = 10;
        [SerializeField]
        private bool openPortOnStart;
        [SerializeField]
        private bool showDebugs = true;
        [SerializeField]
        [Tooltip("Available rates: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200")]
        private int baudRate = 9600;

        private readonly List<int> baudRates = new List<int> {300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200};
        private readonly List<string> portNames = new List<string>();

        private SerialPort serialPort;
        private string currentComPort = "COM5";

        private string rawData;
        private string[] dataTokens;
        private Coroutine fetchDataCoroutine;

        private bool IsSerialPortOpen => serialPort != null && serialPort.IsOpen;
        private bool IsValidSerialPort => serialPort != null;

        public Action<string[], string> SerialDataParsed;
        public Action SerialPortOpenEvent;
        public Action SerialPortCloseEvent;
        public Action<string> SerialPortSentDataEvent;

        public void SendSerialData(string data, bool sendAsLine = false)
        {
            if (!IsSerialPortOpen)
            {
                Log("Trying to SendSerialData with SerialPort closed / null", LogSeverity.Error);
                return;
            }

            if (sendAsLine)
                serialPort.Write(data);
            else
                serialPort.WriteLine(data);

            Log($"Sent data: {data}");

            SerialPortSentDataEvent?.Invoke(data);
        }

        public void SendSerialDataAsLine(string data)
        {
            SendSerialData(data, true);
        }

        public void OpenSerialPort()
        {
            Log("Opening Serial Port!");
            try
            {
                UpdateComPort();
                Debug.Assert(baudRates.IndexOf(baudRate) != -1, "Invalid baudRate");

                serialPort = new SerialPort(currentComPort, baudRate)
                {
                    ReadTimeout = readTimeout, WriteTimeout = writeTimeout
                };

                serialPort.Open();
                Log("SerialPort successfully opened!");
                SerialPortOpenEvent?.Invoke();

                StartFetchingData();
            }
            catch (Exception ex)
            {
                Log($"Error 1: {ex.Message}", LogSeverity.Error);
            }
        }

        public void CloseSerialPort()
        {
            try
            {
                serialPort.Close();
                serialPort = null;
                Log("Serial port closed!");
                SerialPortCloseEvent?.Invoke();
            }
            catch (Exception ex)
            {
                if (IsSerialPortOpen)
                {
                    Log("Error 2A: Port already closed!", LogSeverity.Warning);
                }
                else
                {
                    Log($"Error 2B: {ex.Message}", LogSeverity.Error);
                }
            }
        }

        private IEnumerator FetchSerialData()
        {
            while (fetchDataCoroutine != null)
            {
                FetchSerialDataLine();
                yield return null;
            }
        }

        private void StartFetchingData()
        {
            if (fetchDataCoroutine != null)
                StopFetchingData();

            fetchDataCoroutine = StartCoroutine(nameof(FetchSerialData));
        }

        private void StopFetchingData()
        {
            StopCoroutine(fetchDataCoroutine);
            fetchDataCoroutine = null;
            Log("Stopped Serial Loop Coroutine!");
        }

        private void FetchSerialDataLine()
        {
            try
            {
                if (!IsSerialPortOpen) return;

                string newData = serialPort.ReadLine();

                if (String.IsNullOrEmpty(newData)) return;

                rawData = newData;
                dataTokens = rawData.Split(',');
                Log($"Data received via port: {rawData}");

                SerialDataParsed?.Invoke(dataTokens, rawData);
            }
            catch (TimeoutException) {} // Ignore timeouts
            catch (Exception ex)
            {
                if (IsSerialPortOpen)
                    Log($"Error 4: {ex.Message}", LogSeverity.Error);
                else
                    Log("Error 5: Port Closed during GenericSerialLoop!");
            }
        }

        private void PopulateComPorts()
        {
            portNames.Clear();

            foreach (string portName in SerialPort.GetPortNames())
            {
                portNames.Add(portName);

                Log($"Port found: {portName}");
            }
        }

        private void UpdateComPort()
        {
            PopulateComPorts();

            var portIndex = portNames.IndexOf(currentComPort);
            currentComPort = portIndex + 1 <= portNames.Count - 1 ? portNames[portIndex + 1] : portNames[0];
        }

        private void Start()
        {
            if (openPortOnStart)
                OpenSerialPort();
        }

        private void OnDestroy()
        {
            if (IsSerialPortOpen)
                CloseSerialPort();

            if (fetchDataCoroutine != null)
                StopFetchingData();
        }

        #region Logger

        private enum LogSeverity {Info, Warning, Error}

        private void Log(string message, LogSeverity logSeverity = LogSeverity.Info)
        {
            if (!showDebugs && logSeverity != LogSeverity.Error) return;

            if (logSeverity == LogSeverity.Info)
                Debug.Log(message);

            else if (logSeverity == LogSeverity.Warning)
                Debug.LogWarning(message);

            else
                Debug.LogError(message);
        }

        #endregion Logger
    }
}