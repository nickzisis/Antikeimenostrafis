package ce326.hw2;

public class MagicShield extends BoardElement implements Consumable {
    private int energyGain;
    private int shieldGain;

    public MagicShield(int row, int column, String symbol, Character type){
        super(row, column, symbol); 
        
        switch (type){
            case 'r' -> this.shieldGain = 6;
            case 'b' -> this.shieldGain = 3;
            default -> this.shieldGain = 0;
        }
    }

    @Override
    public int gainEnergy() {
        return this.energyGain;
    }

    @Override
    public int gainShield() {
        return this.shieldGain;
    }
}