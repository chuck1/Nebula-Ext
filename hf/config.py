import pbs.classes.Dynamic

l = pbs.classes.Dynamic.Dynamic("nebula_ext_hf", self)

l.require("galaxy_std")
l.require("galaxy_console")
l.require("nebula_fnd0")

l.make()

