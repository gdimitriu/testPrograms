package producerconsumers.serializers;

import org.apache.kafka.common.errors.SerializationException;
import org.apache.kafka.common.header.Headers;
import org.apache.kafka.common.serialization.Deserializer;
import producerconsumers.data.Customer;

import java.nio.ByteBuffer;
import java.util.Map;

public class CustomerDeserializer implements Deserializer<Customer> {
    @Override
    public Customer deserialize(String topic, byte[] data) {
        int id;
        int nameSize;
        String name;
        try {
            if (data == null) {
                return null;
            }
            if (data.length < 8) {
                throw new SerializationException("Size of data received by deserializer is shorter than expected !");
            }
            ByteBuffer buffer = ByteBuffer.wrap(data);
            id = buffer.getInt();
            nameSize = buffer.getInt();

            byte[] nameBytes = new byte[nameSize];
            buffer.get(nameBytes);
            name = new String(nameBytes, "UTF-8");
            return new Customer(id, name);
        } catch (Exception e) {
            throw new SerializationException("Error when deserializing " + e);
        }
    }

    @Override
    public void configure(Map<String, ?> configs, boolean isKey) {
        //do nothing
    }

    /**
     * I do not know what to do with headers !!!
     * @param topic the topic
     * @param headers the headers ?????
     * @param data the data
     * @return Customer Instance
     */
    @Override
    public Customer deserialize(String topic, Headers headers, byte[] data) {
        return deserialize(topic, data);
    }

    @Override
    public void close() {
        //do nothing
    }
}
