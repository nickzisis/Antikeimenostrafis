package ce326.hw2;

public class Actor extends BoardElement {
    private int energy;
    private int shield;

    public Actor(int row, int column, int energy) {
        super(row, column, "X");
        this.energy = energy;
        this.shield = 0;
    }

    public int getEnergy() {
        return this.energy;
    }

    public int getShield() {
        return this.shield;
    }

    public void addEnergy(int energy) {
        this.energy = this.energy + energy;
    }

    public void addShield(int shield) {
        this.shield = this.shield + shield;
    }

    public void removeEnergy(int energy) {
        this.energy = this.energy - energy;
    }

    public void removeShield(int shield) {
        this.shield = this.shield - shield;
    }
}