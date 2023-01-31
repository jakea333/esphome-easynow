import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ['logger', 'proxy_base']
AUTO_LOAD = ['proxy_base']

CONF_ESPNOW_CHANNEL = "espnow_channel"
CONF_TRANSMITTERS = "transmitters"

CONF_TRANSMITTER_MAC_ADDRESS = "mac_address"


ns = cg.esphome_ns.namespace('proxy_receiver')
ProxyReceiverComponent = ns.class_('ProxyReceiverComponent', cg.Component)

SENDER_SCHEMA = cv.Schema({
    cv.Required(CONF_TRANSMITTER_MAC_ADDRESS): cv.mac_address
})

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ProxyReceiverComponent),
    cv.Required(CONF_ESPNOW_CHANNEL): cv.int_,
    cv.Required(CONF_TRANSMITTERS): cv.ensure_list(SENDER_SCHEMA),
})


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    cg.add(var.set_espnow_channel(config[CONF_ESPNOW_CHANNEL]))

    for outputConf in config.get(CONF_TRANSMITTERS, []):
        cg.add(var.add_transmitter(outputConf[CONF_TRANSMITTER_MAC_ADDRESS].as_hex, 10))
