struct Fraction{
	int num, den;
	
	Fraction(int _num, int _den){
		num = _num;
		den = _den;
	}
	
	Fraction operator+ (Fraction const &f) const{
		if(den == f.den){
			return Fraction( num+f.num, den );
		}
		return Fraction( num*f.den + f.num*den, den*f.den );
	}
	
	Fraction operator- (Fraction const &f) const{
		if(den == f.den){
			return Fraction( num-f.num, den );
		}
		return Fraction( num*f.den - f.num*den, den*f.den );
	}
	
	Fraction operator* (Fraction const &f) const{
		return Fraction( num*f.num, den*f.den);
	}
	Fraction operator/ (Fraction const &f) const{
		return Fraction( num*f.den, den*f.num);
	}
	
	bool operator< (Fraction const &f) const{
		return num*1.0/den < f.num*1.0/f.den;
	}

	bool operator> (Fraction const &f) const{
		return num*1.0/den > f.num*1.0/f.den;
	}
	void reduce(){
		while(__gcd(num, den)!=1){
			int g = __gcd(num, den);
			num /= g;
			den /= g;
		}
	}
};

ostream& operator<<(ostream& out, const Fraction &f){
	out << f.num << "/" << f.den;
}
