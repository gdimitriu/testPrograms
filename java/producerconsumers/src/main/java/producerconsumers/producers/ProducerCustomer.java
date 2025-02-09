package producerconsumers.producers;

import org.apache.kafka.clients.producer.Callback;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.clients.producer.RecordMetadata;
import producerconsumers.data.Customer;
import producerconsumers.serializers.CustomerSerializer;

import java.util.Properties;

public class ProducerCustomer {

    private void sendSynchronous(final KafkaProducer<String, Customer> producer, final ProducerRecord<String, Customer> producerRecord) {
        try {
            RecordMetadata result = producer.send(producerRecord).get();
            System.out.println("SendSynchronous topic : " + result.topic() + " : " + result.timestamp());
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }

    /**
     * callback for producer with asynchronous send.
     */
    private class ProducerCallback implements Callback {
        @Override
        public void onCompletion(RecordMetadata metadata, Exception exception) {
            if (exception != null) {
                exception.printStackTrace();
            } else {
                System.out.println("SendAsync topic : " + metadata.topic() + " : " + metadata.timestamp());
            }
        }
    }
    private void sendAsync(final KafkaProducer<String, Customer> producer, final ProducerRecord<String, Customer> producerRecord) {
        producer.send(producerRecord, new ProducerCallback());
    }

    public static void main(String...args) {
        if (args.length != 2) {
            System.err.println("Call using : ip-address port");
            System.exit(-1);
        }
        Properties kafkaProps = new Properties();
        kafkaProps.put("bootstrap.servers", args[0] + ":" + args[1]);
        kafkaProps.put("group.id","CountryCounter");
        kafkaProps.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        kafkaProps.put("value.serializer", CustomerSerializer.class.getName());
        KafkaProducer<String, Customer> producer = new KafkaProducer<>(kafkaProps);
        ProducerRecord<String, Customer> record = new ProducerRecord<String, Customer>("CustomerClassCountry", "Precision Products", new Customer(12345, "Me"));
        ProducerCustomer producerSend = new ProducerCustomer();

        producerSend.sendSynchronous(producer, record);
        record = new ProducerRecord<>("CustomerClassCountry", "Biomedical Materials", new Customer(54321, "You"));
        producerSend.sendAsync(producer, record);
    }
}
