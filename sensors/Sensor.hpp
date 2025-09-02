#pragma once
#include <iostream>
#include <string>
#include <variant>
#include <optional>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <cmath>

template< typename T >
class Sensor{
    public:
        struct Identity{
            std::string hardwareID;
            std::string type;

            Identity(const std::string& hardwareID, const std::string& type): hardwareID(hardwareID), type(type){}
        };

    private:
        std::string label;
        std::variant<Identity, std::string> source;
        std::optional<std::string> unit;
        std::vector<T> measurements;

    public:
        explicit Sensor(const std::string& label, const std::variant<Identity, std::string>& source,
            const std::optional<std::string>& unit = std::nullopt)
            : label(label), source(source), unit(unit) {}
            
        const std::string& getLabel() const { return label; }
        const std::optional<std::string>& getUnit() const { return unit; }
        const std::variant<Identity, std::string>& getSource() const { return source; }
        const std::vector<T>& getMeasurments() const { return measurements; }

        T getRMS() const {
            if(measurements.empty()){
                return T(0);
            }
            T suma = std::accumulate(measurements.begin(), measurements.end(), 
                T(0),
                [](T accumltd, T value){ return accumltd + value*value; }
                );
            return static_cast<T>(std::sqrt(suma/ static_cast<double>(measurements.size())));
        }

        T getMin() const {
            if (measurements.empty()) {
                return T(0);
            }
            return *std::min_element(measurements.begin(), measurements.end());
        }

        bool operator>(const Sensor& other) const {
            if( label == other.label){
                return measurements.size() > other.measurements.size();
            }
            return label > other.label;
        }

        bool operator!=(const Sensor& other) const {
            return label != other.label;
        }

        Sensor& operator<<( const T& pomiar) {
            measurements.push_back(pomiar);
            return *this;
        }

        std::ostream& writeToStream(std::ostream& os) const {
            os << label << " ";
            if (std::holds_alternative<Identity>(getSource())) {
                const Identity& identity = std::get<Identity>(getSource());
                os << "[" << identity.hardwareID << ", " << identity.type << "]";
            } else {
                os << "[" << std::get<std::string>(getSource()) << "]";
            }
            os << " RMS: " << getRMS() << ", Min: " << getMin() << "\n";
            if (unit.has_value()) {
                os << "Unit: " << getUnit().value() << "\n";
            }
            return os;
        }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Sensor<T>& sensor) {
    return sensor.writeToStream(os);
}