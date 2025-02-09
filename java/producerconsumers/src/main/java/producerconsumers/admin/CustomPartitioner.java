package producerconsumers.admin;

import org.apache.kafka.clients.producer.Partitioner;
import org.apache.kafka.common.Cluster;
import org.apache.kafka.common.PartitionInfo;
import org.apache.kafka.common.InvalidRecordException;
import org.apache.kafka.common.utils.Utils;

import java.util.List;
import java.util.Map;

/**
 * custom partitioner ... the partner is set by property custom.partitioner.key
 */
public class CustomPartitioner implements Partitioner {

    /** the name of the key which is using this custom partitioner */
    private String customKey;
    @Override
    public int partition(String topic, Object key, byte[] keyBytes, Object value, byte[] valueBytes, Cluster cluster) {
        List<PartitionInfo> partitions = cluster.partitionsForTopic(topic);
        int numPartitions = partitions.size();
        if ((keyBytes == null) || (key instanceof String)) {
            throw new InvalidRecordException("We expect all messages " + " to have customer name as key");
        }
        if(((String) key).equals(customKey)) {
            return numPartitions - 1; //go to the last partition.
        }
        //rest of record hashed to the rest or partitions
        return (Math.abs(Utils.murmur2(keyBytes)) % (numPartitions -1));
    }

    @Override
    public void close() {
        //does nothing
    }

    @Override
    public void configure(Map<String, ?> configs) {
        customKey = configs.get("custom.partitioner.key").toString();
    }
}
