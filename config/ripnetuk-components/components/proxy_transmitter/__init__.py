import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ['logger', 'proxy_base']
AUTO_LOAD = ['proxy_base']

ns = cg.esphome_ns.namespace('proxy_transmitter')
ProxyTransmitterComponent = ns.class_('ProxyTransmitterComponent', cg.Component)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ProxyTransmitterComponent),
})


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
