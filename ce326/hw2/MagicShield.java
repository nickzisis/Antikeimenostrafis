package ce326.hw2;

public class MagicShield extends BoardElement implements Consumable {
    private int energyGain;
    private int shieldGain;

    public MagicShield(int row, int column, String symbol){
        super(row, column, symbol); 
        
        switch (symbol.charAt(1)){
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