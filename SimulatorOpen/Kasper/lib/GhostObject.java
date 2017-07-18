public class GhostObject{

  private class Leg{
    PartLeg ghostSinglePart[] = new PartLeg[3];
  }

  private Leg ghostSingleLeg[] = new Leg[4];

  public GhostObject(){
    PARTNAME[] orderPart = new PARTNAME[]{PARTNAME.FEMUR, PARTNAME.TIBIA, PARTNAME.ROTATION};
    for (int i=0; i<ghostSingleLeg.length; i++){
      for (int j=0; j<orderPart.length; j++){
        ghostSingleLeg[i].ghostSinglePart[j] = new PartLeg();
        ghostSingleLeg[i].ghostSinglePart[j].setPart(orderPart[j]);
        try {
          ghostSingleLeg[i].ghostSinglePart[j].setValue(PartLeg.getDefaultValue());
        }
        catch (ValueGhostPartErrorException name){

        }
      }
    }
  }

}
