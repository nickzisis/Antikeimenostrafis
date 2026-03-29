package ce326.hw2;

public class Food extends BoardElement implements Consumable {
    private int energyGain;
    private int shieldGain;

    public Food(int row,  int column, String symbol){
        super(row, column, symbol);
        
        switch (symbol.charAt(1)) {
            case 'r' -> this.energyGain = 14;
            case 'b' -> this.energyGain = 10;
            case 'g' -> this.energyGain = 6;
            default -> this.energyGain = 0;
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
