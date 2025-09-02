#pragma once
#include <unordered_map>
#include <list>
#include <string>
#include <iostream>
#include "Sensor.hpp"

template< typename T >
class SensorCollection{
    private:
        std::unordered_map<std::string, std::list<Sensor<double>>> sensorsByType;

    public:
        void addSensor(const std::string& type, const Sensor<double>& sensor);
        const std::unordered_map<std::string, std::list<Sensor<double>>>& getSensorsByType() const;
        std::list<Sensor<double>> getAllSensors() const;
};

std::ostream& operator<<(std::ostream& os, const SensorCollection& collection);