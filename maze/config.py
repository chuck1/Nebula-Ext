import pbs.classes.Dynamic

l = pbs.classes.Dynamic.Dynamic("nebula_ext_maze", self)

l.require("maze")
l.require("galaxy_std", whole=True)
l.require("galaxy_net", whole=True)
l.require("galaxy_console", whole=True)
l.require("nebula_fnd0", "dynamic")

l.make()

