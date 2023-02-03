import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID
from esphome.components import sensor

DEPENDENCIES = ['logger']
AUTO_LOAD = ['proxy_base', 'sensor', 'switch']

CONF_ESPNOW_CHANNEL = "espnow_channel"
CONF_TRANSMITTERS = "transmitters"


CONF_TRANSMITTER_MAC_ADDRESS = "mac_address"
CONF_TRANSMITTER_NAME = "name"
CONF_TRANSMITTER_PROXIED_SENSORS = "proxied_sensors"

CONF_PROXIED_SENSOR_PROXY_ID = "proxy_id"
CONF_PROXIED_SENSOR_NAME = "name"


def validate_proxy_id(value):
    value = cv.string_strict(value)
    value = cv.Length(max=20)(value)
    return value


ns = cg.esphome_ns.namespace('proxy_receiver')
ProxyReceiverComponent = ns.class_('ProxyReceiverComponent', cg.Component)

PROXIED_SENSOR_SCHEMA = cv.All(
    sensor.sensor_schema(
        # ADCSensor,
        # unit_of_measurement=UNIT_VOLT,
        # accuracy_decimals=2,
        # device_class=DEVICE_CLASS_VOLTAGE,
        # state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            # cv.Required(CONF_PIN): validate_adc_pin,
            # cv.Optional(CONF_RAW, default=False): cv.boolean,
            # cv.SplitDefault(CONF_ATTENUATION, esp32="0db"): cv.All(
            #     cv.only_on_esp32, cv.enum(ATTENUATION_MODES, lower=True)
            cv.Required(CONF_PROXIED_SENSOR_PROXY_ID): validate_proxy_id,
            #cv.Required(CONF_PROXIED_SENSOR_NAME): cv.string_strict,

        }
    ))

# PROXIED_SENSOR_SCHEMA = cv.Schema({
#     cv.Required(CONF_PROXIED_SENSOR_PROXY_ID): validate_proxy_id,
#     cv.Required(CONF_PROXIED_SENSOR_NAME): cv.string_strict,

# })


TRANSMITTER_SCHEMA=cv.Schema({
    cv.Required(CONF_TRANSMITTER_MAC_ADDRESS): cv.mac_address,
    cv.Required(CONF_TRANSMITTER_NAME): cv.string_strict,
    cv.Required(CONF_TRANSMITTER_PROXIED_SENSORS): cv.ensure_list(PROXIED_SENSOR_SCHEMA)
})

CONFIG_SCHEMA=cv.Schema({
    cv.GenerateID(): cv.declare_id(ProxyReceiverComponent),
    cv.Required(CONF_ESPNOW_CHANNEL): cv.int_,
    cv.Required(CONF_TRANSMITTERS): cv.ensure_list(TRANSMITTER_SCHEMA),
})


def to_code(config):
    var=cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    #yield sensor.register_sensor(var, config)

    cg.add(var.set_espnow_channel(config[CONF_ESPNOW_CHANNEL]))

    for outputConf in config.get(CONF_TRANSMITTERS, []):
        cg.add(var.add_transmitter(
            outputConf[CONF_TRANSMITTER_MAC_ADDRESS].as_hex, outputConf[CONF_TRANSMITTER_NAME]))
        for proxiedSensorConf in outputConf.get(CONF_TRANSMITTER_PROXIED_SENSORS, []):
            cg.add(var.add_proxied_sensor(
                outputConf[CONF_TRANSMITTER_MAC_ADDRESS].as_hex,
                proxiedSensorConf[CONF_PROXIED_SENSOR_PROXY_ID],
                proxiedSensorConf[CONF_PROXIED_SENSOR_NAME],
            ))
