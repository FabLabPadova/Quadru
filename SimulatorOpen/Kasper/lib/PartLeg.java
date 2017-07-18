enum PARTNAME{
  FEMUR, TIBIA, ROTATION;
}

class ValueGhostPartErrorException extends Exception
{
      // Parameterless Constructor
      public ValueGhostPartErrorException() {}

      // Constructor that accepts a message
      public ValueGhostPartErrorException(String message)
      {
         super(message);
      }
 }

public class PartLeg{

  private static int minValue = 800, maxValue = 2200;
  private String part;
  private int value;

  public void setPart(PARTNAME _part){
    part = assocPartName(_part);
  }

  public void setValue(int _value) throws ValueGhostPartErrorException{
    if ((_value>= minValue) && (_value<= maxValue)){
      throw new ValueGhostPartErrorException("Value : "+_value+" is invalid.");
    }
    value = _value;
  }

  public int getValue(){
    return value;
  }

  public String getPart(){
    return part;
  }

  private static String assocPartName(PARTNAME _partname){
    switch (_partname){
      case FEMUR:
        return "Femore";
      case TIBIA:
        return "Tibia";
      case ROTATION:
        return "Rotazione";
    }
    return null;
  }

  public static int getDefaultValue(){
    return Math.round(maxValue + minValue / 2);
  }


}
