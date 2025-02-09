package producerconsumers.consumers;

import org.apache.kafka.clients.consumer.*;
import org.apache.kafka.common.TopicPartition;
import producerconsumers.data.Customer;
import producerconsumers.serializers.CustomerDeserializer;

import java.time.Duration;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

public class ConsumerCustomer {

    public static void main(String...args) {
        if (args.length != 3) {
            System.err.println("Call using : ip-address port groupId");
            System.exit(-1);
        }
        Properties kafkaProps = new Properties();
        kafkaProps.put("bootstrap.servers", args[0] + ":" + args[1]);
        kafkaProps.put("group.id", args[2]);
        kafkaProps.put("enable.auto.commit", "false"); //true if you remove commitSync
        kafkaProps.put("auto.commit.interval.ms", "1000");
        kafkaProps.put("session.timeout.ms", "30000");
        kafkaProps.put("client.id", "my");
        kafkaProps.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        kafkaProps.put("value.deserializer", CustomerDeserializer.class.getName());
        KafkaConsumer<String, Customer> consumer = new KafkaConsumer<>(kafkaProps);
        consumer.subscribe(Arrays.asList("CustomerClassCountry"));
        System.out.println("Consumer subscribed to topic " + "CustomerClassCountry");
        consumer.subscription().stream().forEach( System.out::println);
        Map<TopicPartition, OffsetAndMetadata> currentOffsets = new HashMap<>();
        try {
            while(true) {
                ConsumerRecords<String, Customer> records = consumer.poll(Duration.ofMillis(100));
                for(ConsumerRecord<String, Customer> record : records) {
                    System.out.println("topic=" + record.topic() + " key=" + record.key() + " value=" + record.value());
//                    currentOffsets.put(new TopicPartition(record.topic(), record.partition()), new OffsetAndMetadata(record.offset() + 1, "no metadata"));
                }
                //commit should be done after processing all the records in the collection
//                consumer.commitSync();
                //option is the async
                consumer.commitAsync(new OffsetCommitCallback() {
                    @Override
                    public void onComplete(Map<TopicPartition, OffsetAndMetadata> offsets, Exception exception) {
                        if (exception != null) {
                            System.err.println("Commit failed for offsets: " + offsets + " with exception " + exception.getLocalizedMessage());
                        }
                    }
                });
                //option commit not all
//                consumer.commitSync(currentOffsets, null); //it could be also async
            }
        } finally {
            try {
                consumer.commitSync();
            } finally {
                consumer.close();
            }
        }
    }
}
