from collections import deque
from typing import Optional, List

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def in_order(root: Optional[TreeNode]):

    if root is None:
        return

    in_order(root.left)
    print(root.val)
    in_order(root.right)

def post_order(root: Optional[TreeNode]):

    if root is None:
        return

    post_order(root.left)
    post_order(root.right)
    print(root.val)

def pre_order(root: Optional[TreeNode]):

    if root is None:
        return

    print(root.val)
    pre_order(root.left)
    pre_order(root.right)


def level_order(root: Optional[TreeNode]) -> List[List[int]]:
    if not root:
        return []

    queue = deque([root])
    res = []

    while queue:
        level_size = len(queue)
        level = []

        for _ in range(level_size):
            current = queue.popleft()
            level.append(current.val)

            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)

        res.append(level)

    return res
