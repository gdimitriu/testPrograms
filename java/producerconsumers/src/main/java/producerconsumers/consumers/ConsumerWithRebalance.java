package producerconsumers.consumers;

import org.apache.kafka.clients.consumer.*;
import org.apache.kafka.common.TopicPartition;
import org.apache.kafka.common.errors.WakeupException;

import java.time.Duration;
import java.util.*;

public class ConsumerWithRebalance {

    private Map<TopicPartition, OffsetAndMetadata> currentOffsets = new HashMap<>();

    private KafkaConsumer<String, String> consumer = null;

    public ConsumerWithRebalance(KafkaConsumer<String, String> consumer) {
        this.consumer = consumer;
    }

    private class HandleRebalance implements ConsumerRebalanceListener {
        @Override
        public void onPartitionsRevoked(Collection<TopicPartition> partitions) {
            System.out.println("Lost partitions in rebalance. " + "Committing current offsets:" + currentOffsets);
            consumer.commitSync(currentOffsets);
        }

        @Override
        public void onPartitionsAssigned(Collection<TopicPartition> partitions) {
            System.out.println("On parttion assigned go to offset 0");
//            for(TopicPartition partition : partitions) {
//                consumer.seek(partition, 0);
//            }
            consumer.seekToBeginning(partitions);
        }
    }

    public void consume() {
        consumer.subscribe(Arrays.asList("CustomerCountry"), new HandleRebalance());
        System.out.println("Consumer subscribed to topic " + "CustomerCountry");
        consumer.subscription().stream().forEach( System.out::println);
        try {
            while(true) {
                ConsumerRecords<String, String> records = consumer.poll(Duration.ofMillis(100));
                for(ConsumerRecord<String, String> record : records) {
                    System.out.println("topic=" + record.topic() + " key=" + record.key() + " value=" + record.value());
                    currentOffsets.put(new TopicPartition(record.topic(), record.partition()), new OffsetAndMetadata(record.offset() + 1, null));
                }
            }
        } catch (WakeupException e) {
            //ignore, we are closing
        } catch (Exception e) {
            System.err.println("Unexpected Error: " + e.getLocalizedMessage());
            e.printStackTrace();
        }
        finally {
            try {
                consumer.commitSync(currentOffsets);
            } finally {
                consumer.close();
                System.out.println("Closed consumer and we are done with this one");
            }
        }
    }

    public static void main(String...args) {
        if (args.length != 3) {
            System.err.println("Call using : ip-address port groupId");
            System.exit(-1);
        }
        Properties kafkaProps = new Properties();
        kafkaProps.put("bootstrap.servers", args[0] + ":" + args[1]);
        kafkaProps.put("group.id", args[2]);
        kafkaProps.put("enable.auto.commit", "true");
        kafkaProps.put("auto.commit.interval.ms", "1000");
        kafkaProps.put("session.timeout.ms", "30000");
        kafkaProps.put("client.id", "my");
        kafkaProps.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        kafkaProps.put("value.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        KafkaConsumer<String, String> consumer = new KafkaConsumer<String, String>(kafkaProps);
        ConsumerWithRebalance consumerWithRebalance = new ConsumerWithRebalance(consumer);
        consumerWithRebalance.consume();
    }
}
