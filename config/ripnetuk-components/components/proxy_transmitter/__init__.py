import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.components import sensor

DEPENDENCIES = ['logger', 'proxy_base']
AUTO_LOAD = ['proxy_base']

CONF_ESPNOW_CHANNEL = "espnow_channel"
CONF_RECEIVER_MAC_ADDRESS = "receiver_mac_address"
CONF_SENSORS = "sensors"

CONF_SENSOR = "sensor"
CONF_PROXY_ID = "proxy_id"

def validate_proxy_id(value):
    value = cv.string_strict(value)
    value = cv.Length(max=255)(value)
    validate_source_shorthand(value)
    return value

SENSOR_SCHEMA = cv.Schema({
    cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
    cv.Required(CONF_PROXY_ID): cv.string,
})


ns = cg.esphome_ns.namespace('proxy_transmitter')
ProxyTransmitterComponent = ns.class_(
    'ProxyTransmitterComponent', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ProxyTransmitterComponent),
    cv.Required(CONF_ESPNOW_CHANNEL): cv.int_,
    cv.Required(CONF_RECEIVER_MAC_ADDRESS): cv.mac_address,
    cv.Required(CONF_SENSORS): cv.ensure_list(SENSOR_SCHEMA),
})


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    cg.add(var.set_espnow_channel(config[CONF_ESPNOW_CHANNEL]))
    cg.add(var.set_receiver_mac_address(
        config[CONF_RECEIVER_MAC_ADDRESS].as_hex))

    for sensor_config in config.get(CONF_SENSORS, []):
        sensor = yield cg.get_variable(sensor_config[CONF_SENSOR])
        cg.add(var.add_sensor(sensor, sensor_config[CONF_PROXY_ID]))