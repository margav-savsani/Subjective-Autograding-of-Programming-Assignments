Journey* choose_one(Journey* x, int start, int finish){
    return &x[start];
}
Journey* choose_two(Journey* x, int start, int finish){
    return &x[finish];
}
Journey* choose_three(Journey* x, int start, int finish){
    return &x[int((start+finish)/2)];
}
Journey* choose_four(Journey* x, int start, int finish){
    return &x[start];
}
