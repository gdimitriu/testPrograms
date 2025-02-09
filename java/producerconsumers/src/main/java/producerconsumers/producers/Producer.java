package producerconsumers.producers;

import org.apache.kafka.clients.producer.Callback;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.clients.producer.RecordMetadata;

import java.util.Properties;

public class Producer {

    private void sendSynchronous(final KafkaProducer<String, String> producer, final ProducerRecord<String, String> producerRecord) {
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
    private void sendAsync(final KafkaProducer<String, String> producer, final ProducerRecord<String, String> producerRecord) {
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
        kafkaProps.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        KafkaProducer<String, String> producer = new KafkaProducer<String, String>(kafkaProps);
        ProducerRecord<String, String> record = new ProducerRecord<>("CustomerCountry", "Precision Products", "France");
        Producer producerSend = new Producer();

        producerSend.sendSynchronous(producer, record);
        record = new ProducerRecord<>("CustomerCountry", "Biomedical Materials", "USA");
        producerSend.sendAsync(producer, record);
    }
}
