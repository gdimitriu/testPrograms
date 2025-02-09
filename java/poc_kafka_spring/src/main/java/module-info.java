module poc.kafka.spring {
    requires spring.boot;
    requires spring.boot.autoconfigure;
    requires spring.beans;
    requires spring.context;
    requires spring.kafka;
    requires kafka.clients;
    requires spring.web;
    requires spring.webmvc;
    requires java.validation;
    requires com.fasterxml.jackson.annotation;
    requires com.fasterxml.jackson.core;
    requires com.fasterxml.jackson.databind;
    requires org.slf4j;
    requires java.annotation;
    requires org.apache.tomcat.embed.core;
    requires spring.messaging;
    opens gdimitriu.kafka_spring.application to spring.core,spring.beans, spring.context;
    opens gdimitriu.kafka_spring.configurations to spring.core, spring.beans, spring.context;
    opens gdimitriu.kafka_spring.controlers to spring.core, spring.beans, spring.context, spring.web, spring.messaging;
}