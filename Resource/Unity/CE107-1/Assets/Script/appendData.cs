using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class appendData : MonoBehaviour
{
    public static int CE_Temperature = 0;
    public static int CE_pm1 = 0;
    public static int CE_RoomCapacity = 0;
    public static double CE_dB = 0;
    public class enviroMQTTStructure{
        public int temperature;
        public int pressure;
        public int humidity;
        public int oxidised;
        public int reduced;
        public int nh3;
        public int lux;
        public int pm1;
        public int pm25;
        public int pm10;

        public int this[string propertyName]{
            get{
                if (propertyName == "temperature"){
                    return temperature;
                }
                else if (propertyName == "pressure"){
                    return pressure;
                }
                else if (propertyName == "humidity"){
                    return humidity;
                }
                else if (propertyName == "pm1"){
                    return pm1;
                }
                else{
                    throw new System.ArgumentException("Invalid property name");
                }
            }
        }
    }
    public string[] enviroSubTopics = { "temperature", "pm1"};
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void updatePanel(List<string> topicStorage, List<string> messageStorage){
        VisualElement baseTemplate = GetComponent<UIDocument>().rootVisualElement.Q("Content");
        
        int lastIndex = messageStorage.Count - 1;
        string[] fullTopicAddress = topicStorage[lastIndex].Split("/");
        string topic = fullTopicAddress[fullTopicAddress.Length - 1];
        if (topic == "enviro"){
            enviroMQTTStructure enviroValues = enviroJson(messageStorage[lastIndex]);
            CE_Temperature = enviroValues.temperature;
            CE_pm1 = enviroValues.pm1;

            foreach(string dataName in enviroSubTopics){
                VisualElement updatingVaildation = GetComponent<UIDocument>().rootVisualElement.Q(dataName);
                if (updatingVaildation == null){
                    VisualElement data = new VisualElement();
                    data.name = dataName;
                    data.AddToClassList("text-content");

                    Label title = new Label(dataName);
                    title.name = "Title";
                    title.AddToClassList("title");
                    data.Add(title);
                    
                    // Label value = new Label((string)enviroValues.GetType().GetProperty(dataName).GetValue(enviroValues, null));
                    Label value = new Label(enviroValues[dataName].ToString());
                    value.name = "Value";
                    value.AddToClassList("value");
                    data.Add(value);

                    baseTemplate.Add(data);
                }else{
                    Label value = updatingVaildation.Query<Label>("Value");
                    value.text = enviroValues[dataName].ToString();
                }
            }
        }else{
            VisualElement updatingVaildation = GetComponent<UIDocument>().rootVisualElement.Q(topic);
            if (updatingVaildation == null){
                VisualElement data = new VisualElement();
                data.name = topic;
                data.AddToClassList("text-content");

                Label title = new Label(topic);
                title.AddToClassList("title");
                title.name = "Title";
                data.Add(title);
                Label value = new Label(System.Math.Round(double.Parse(messageStorage[lastIndex]),2).ToString());
                value.name = "Value";
                value.AddToClassList("value");
                data.Add(value);

                baseTemplate.Add(data);
            }else{
                Label value = updatingVaildation.Query<Label>("Value");
                value.text = System.Math.Round(double.Parse(messageStorage[lastIndex]),2).ToString();
            }
            if(topic == "dB"){
                CE_dB = System.Math.Round(double.Parse(messageStorage[lastIndex]),2);
            }else if(topic == "RoomCapacity"){
                CE_RoomCapacity = int.Parse(messageStorage[lastIndex]);
            }
        }
    }
    public static enviroMQTTStructure enviroJson(string json){
        return JsonUtility.FromJson<enviroMQTTStructure>(json);
    }
}
