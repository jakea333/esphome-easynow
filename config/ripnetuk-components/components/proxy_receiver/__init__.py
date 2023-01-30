import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID

DEPENDENCIES = ['logger']

ns = cg.esphome_ns.namespace('proxy_receiver')
ProxyReceiverComponent = ns.class_('ProxyReceiverComponent', cg.Component)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ProxyReceiverComponent),
})


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
