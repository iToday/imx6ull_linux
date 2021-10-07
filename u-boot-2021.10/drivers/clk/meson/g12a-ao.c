// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <log.h>
#include <asm/io.h>
#include <clk-uclass.h>
#include <dm.h>
#include <regmap.h>
#include <syscon.h>
#include <dt-bindings/clock/g12a-aoclkc.h>

#include "clk_meson.h"

struct meson_clk {
	struct regmap *map;
};

#define AO_CLK_GATE0		0x4c
#define AO_SAR_CLK		0x90

static struct meson_gate gates[] = {
	MESON_GATE(CLKID_AO_SAR_ADC, AO_CLK_GATE0, 8),
	MESON_GATE(CLKID_AO_SAR_ADC_CLK, AO_SAR_CLK, 8),
};

static int meson_set_gate(struct clk *clk, bool on)
{
	struct meson_clk *priv = dev_get_priv(clk->dev);
	struct meson_gate *gate;

	if (clk->id >= ARRAY_SIZE(gates))
		return -ENOENT;

	gate = &gates[clk->id];

	if (gate->reg == 0)
		return 0;

	regmap_update_bits(priv->map, gate->reg,
			   BIT(gate->bit), on ? BIT(gate->bit) : 0);

	return 0;
}

static int meson_clk_enable(struct clk *clk)
{
	return meson_set_gate(clk, true);
}

static int meson_clk_disable(struct clk *clk)
{
	return meson_set_gate(clk, false);
}

static int meson_clk_probe(struct udevice *dev)
{
	struct meson_clk *priv = dev_get_priv(dev);

	priv->map = syscon_node_to_regmap(dev_ofnode(dev_get_parent(dev)));
	if (IS_ERR(priv->map))
		return PTR_ERR(priv->map);

	return 0;
}

static struct clk_ops meson_clk_ops = {
	.disable	= meson_clk_disable,
	.enable		= meson_clk_enable,
};

static const struct udevice_id meson_clk_ids[] = {
	{ .compatible = "amlogic,meson-g12a-aoclkc" },
	{ }
};

U_BOOT_DRIVER(meson_clk_axg) = {
	.name		= "meson_clk_g12a_ao",
	.id		= UCLASS_CLK,
	.of_match	= meson_clk_ids,
	.priv_auto	= sizeof(struct meson_clk),
	.ops		= &meson_clk_ops,
	.probe		= meson_clk_probe,
};
