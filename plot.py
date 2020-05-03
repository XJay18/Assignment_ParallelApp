import matplotlib.pyplot as plt

m = [100, 200, 300, 400, 500]
m_x = [0.0727148, 0.142194, 0.219311, 0.299292, 0.346659]
m_y = [0.0337497, 0.0556765, 0.0735166, 0.0927854, 0.123935]

n = [100, 200, 300, 400, 500]
n_x = [0.0727148, 0.141662, 0.203834, 0.274754, 0.324804]
n_y = [0.0337497, 0.0420715, 0.0590831, 0.106442, 0.0854896]

slot = [10000, 20000, 30000, 40000, 50000]
integral_x = [0.777408, 1.61001, 2.48181, 3.15643, 3.96604]
integral_y = [0.200672, 0.397909, 0.569428, 0.840211, 1.03982]

list_length = [1000, 2000, 3000, 4000, 5000]
sort_x = [3.72927, 14.4251, 30.5807, 57.7083, 87.6708]
sort_y = [2.16788, 5.62582, 9.13162, 15.075, 20.7366]


def plot1m():
    plt.figure()
    plt.title("MatVec Multiplication m*n (n=100)")
    plt.plot(m, m_x, label="sequential")
    plt.plot(m, m_y, label="parallel")
    plt.legend(loc="best")
    plt.xlabel("m")
    plt.ylabel("ms per task")
    plt.show()


def plot1n():
    plt.figure()
    plt.title("MatVec Multiplication m*n (m=100)")
    plt.plot(n, n_x, label="sequential")
    plt.plot(n, n_y, label="parallel")
    plt.legend(loc="best")
    plt.xlabel("n")
    plt.ylabel("ms per task")
    plt.show()


def plot2():
    plt.figure()
    plt.title("Trap Integral")
    plt.plot(slot, integral_x, label="sequential")
    plt.plot(slot, integral_y, label="parallel")
    plt.legend(loc="best")
    plt.xlabel("#trapezoids")
    plt.ylabel("ms per task")
    plt.show()


def plot3():
    plt.figure()
    plt.title("Odd Even Sorting")
    plt.plot(list_length, sort_x, label="sequential")
    plt.plot(list_length, sort_y, label="parallel")
    plt.legend(loc="best")
    plt.xlabel("#list_length")
    plt.ylabel("ms per task")
    plt.show()


if __name__ == "__main__":
    plot3()
    pass
