
class Pair:
    def __init__(self, rhs: str, lhs:str) -> None:
        self.rhs = rhs
        self.lhs = lhs

    def get_rhs(self) -> str:
        return self.rhs

    def get_lhs(self) -> str:
        return self.lhs

    
def attribute_closure(functional_dependencies: dict[str, str], attributes: list[str], attribute: str) -> list[str]:
    
    result = []
    attr = attribute
    changed = True    

    while changed: 
        
        result.append(functional_dependencies[attribute])

        



                 
    return result
