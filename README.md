# Kinova Gravity Compensation Controller

An **[mc_rtc](https://jrl.cnrs.fr/mc_rtc/) FSM controller** for **gravity compensation in torque control** on the **Kinova Gen3** robot.

This controller is based on the framework introduced in
**[Demonstrating a Control Framework for Physical Human–Robot Interaction Toward Industrial Applications](https://industry-ready-phri.github.io/)**, which proposes a safe torque-control approach for pHRI using a **second-order Quadratic Program (QP)** with strict kinematic and collision constraints.

---

## Control Law

The commanded torque is:

```
τ_d = M(q) q̈* + C(q, q̇) q̇ + g(q) − τ_ext
```

The desired acceleration `q̈*` is provided by the QP and, when unconstrained, is:

```
q̈* = Kp (q − q_d) − Kd q̇ + Γ M⁻¹ τ_ext
```

* **Γ = 0** → stiff, non-compliant behavior
* **Γ = 1** → compliant behavior

---

## FSM States

* **Init**
  High stiffness, non-compliant
  `Kp = 100, Kd = 2√Kp, Γ = 0`

* **GravityCompensationDamped**
  Zero stiffness, low damping, compliant
  `Kp = 0, Kd = 5, Γ = 1`

* **LowGainsResetTarget**

  * External forces detected → low gains, compliant
  * No external forces → high stiffness, target reset to current position

---

## Dependency

* [`industry-ready-phri/mc-rtc-superbuild`](https://github.com/industry-ready-phri/mc-rtc-superbuild)

---

## Usage

In your `mc_rtc.yaml`:

```yaml
MainRobot: Kinova
Enabled: KinovaGravityCompensationController
Plugins: [ExternalForcesEstimator]
```

Compatible with all Kinova variants:
`KinovaGripper`, `KinovaCamera`, `KinovaCameraGripper`, `KinovaBotaDS4`, `KinovaBota`
(just change `MainRobot` accordingly).

---

## Run

Use `mc_mujoco` or `mc_kortex` as described in
[`mc-rtc-superbuild`](https://github.com/industry-ready-phri/mc-rtc-superbuild).
