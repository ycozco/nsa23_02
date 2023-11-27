package sistemas_distribuidos.lab01;

public class Consumidor extends Thread {
    private CubbyHole cubbyhole;
    private int numero;

    public Consumidor(CubbyHole c, int numero) {
        cubbyhole = c;
        this.numero = numero;
    }

    public void run() {
        int value = 0;
        for (int i = 0; i < 10; i++) {
            value = cubbyhole.get();
            System.out.println("Consumidor #" + this.numero + " obtiene: " + value);
        }
    }
}

public class CubbyHole {
    private int contents;
    private boolean available = false;

    public synchronized int get() {
        while (available == false) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        available = false;
        notifyAll();
        return contents;
    }

    public synchronized void put(int value) {
        while (available == true) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        contents = value;
        available = true;
        notifyAll();
    }
}

public class Demo {
    public static void main(String[] args) {
        CubbyHole cub = new CubbyHole();
        Consumidor cons = new Consumidor(cub, 1);
        Productor prod = new Productor(cub, 1);
        prod.start();
        cons.start();
    }
}

public class Productor extends Thread {
    private CubbyHole cubbyhole;
    private int numero;

    public Productor(CubbyHole c, int numero) {
        cubbyhole = c;
        this.numero = numero;
    }

    public void run() {
        for (int i = 0; i < 10; i++) {
            cubbyhole.put(i);
            System.out.println("Productor #" + this.numero + " pone: " + i);
            try {
                sleep((int) (Math.random() * 100));
            } catch (InterruptedException e) {
            }
        }
    }
}
